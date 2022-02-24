#include "MyForm.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <ctime>
#include "Data.h"
#include <stdio.h>
#include <fcntl.h> 
#include <io.h>
#include <stdio.h>
#include "Spline.h"
#include <time.h>
#include <thread>
#include <array>

#pragma comment(lib, "user32.lib")


using namespace System;
using namespace System::Windows::Forms;
using std::to_string;
using std::string;
using std::ifstream;
using std::ofstream;

static int sprayCount = 0;
bool isCrouched = false;


class Settings {
private:
    string filename = "profile.rapid";

    double ingameFOV = 90.0;
    double playerSens = 0.5;
    int interpolationType = 0;
    bool regeneratePerCycle = true;
    int currentWeapon = 0;
    int currentScope = 0;

    std::vector<double> weapon_inaccuracy = std::vector<double>();

    void save() {
        ofstream f(filename);
        f << "FOV:\n";
        f << to_string(ingameFOV) + "\n";
        f << "Sens:\n";
        f << to_string(playerSens) + "\n";
        f << "-- DO NOT EDIT THESE --\n";
        f << to_string(currentWeapon) + "\n";
        f << to_string(currentScope) + "\n";
        f << to_string(interpolationType) + "\n";
        f << to_string((regeneratePerCycle ? 1 : 0)) + "\n";
        for (int i = 0; i < weapon_inaccuracy.size(); i++) {
            f << to_string(weapon_inaccuracy.at(i)) + "\n";
        }
        f.close();
    }
    string nextLn(ifstream& f) {
        string res;
        getline(f, res);
        return res;
    }



public:
    Settings() {
        load();
    }
    void load() {

        for (int i = 0; i < GameData::weapons.size(); i++) {
            weapon_inaccuracy.push_back(0);
        }
        ifstream f(filename);
        if (!f.good()) { // REMOVE THE OR TRUE TO ENABLE SAVING
            save();
            return;
        }
        nextLn(f);
        ingameFOV = stod(nextLn(f));
        nextLn(f);
        playerSens = stod(nextLn(f));
        nextLn(f);
        currentWeapon = stoi(nextLn(f));
        currentScope = stoi(nextLn(f));
        interpolationType = stoi(nextLn(f));
        regeneratePerCycle = (stoi(nextLn(f)) == 1);
        weapon_inaccuracy.clear();
        for (int i = 0; i < GameData::weapons.size(); i++) {
            weapon_inaccuracy.push_back(stod(nextLn(f)));
        }
        f.close();
        
    }

    double getIngameFOV() {
        return ingameFOV;
    }
    bool getRegeneratePerCycle() {
        return regeneratePerCycle;
    }
    
    int getInterpolationType() {
        return interpolationType;
    }

    double getPlayerSens() {
        return playerSens;
    }
    int getCurrentWeapon() {
        return currentWeapon;
    }
    int getCurrentScope() {
        return currentScope;
    }
    double getCurrentInaccuracy() {
        return weapon_inaccuracy.at(currentWeapon);
    }
    void setIngameFOV(double value) {
        ingameFOV = value;
        save();
    }

    void setInterpolationType(int value) {
        interpolationType = value;
        save();
    }
    
    void setPlayerSens(double value) {
        playerSens = value;
        save();
    }
    void setCurrentWeapon(int value) {
        currentWeapon = value;
        save();
    }
    void setRegeneratePerCycle(bool val) {
        regeneratePerCycle = val;
        save();
    }
    void setCurrentScope(int value) {
        currentScope = value;
        save();
    }
    void setInaccuracy(double value) {
        weapon_inaccuracy.at(currentWeapon)=value;
        save();
    }
};

void sleep(int ms)
{
    LONGLONG timerResolution;
    LONGLONG wantedTime;
    LONGLONG currentTime;

    QueryPerformanceFrequency((LARGE_INTEGER*)&timerResolution);
    timerResolution /= 1000;

    QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
    wantedTime = currentTime / timerResolution + ms;
    currentTime = 0;
    while (currentTime < wantedTime)
    {
        QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
        currentTime /= timerResolution;
    }
}

class PatternGenerator {
private:

    weapon setWeapon;
    scope setScope;

    double playerFOV;
    double playerSens;
    double weapon_inaccuracy;
    double recoilDiffY = 0;
    double recoilDiffX = 0;

    double randomize(double val, double diffToOptimum) {
        if (weapon_inaccuracy == 0) return val;
        val += diffToOptimum;
        int arg = (rand() & 1) * 2 - 1;
        double percent = rand() % (int)((weapon_inaccuracy * 10.0)) / 10.0;
        double amount = percent * val / 100.0;
        double diff = amount * arg;
        return val + diff;
    }

    double getRecoilXRand(int index) {
        double recoil = getRecoilX(index);
        double rnd = randomize(recoil, recoilDiffX);
        recoilDiffX = recoil - rnd;
        return rnd;
    }


    double getRecoilYRand(int index) {
        double recoil = getRecoilY(index);
        double rnd = randomize(recoil, recoilDiffY);
        recoilDiffY = recoil - rnd;
        return rnd;
    }

    void genWithoutInterpolation() {
        double delay = getRoundTime();
        double x_ = 0;
        double y_ = 0;
        for (int o = 0; o < setWeapon.recoilPattern.size(); o++)
        {
            for (int i = 1; i <= (int)delay; ++i)
            {

                x.push_back(((int)x_));
                y.push_back(((int)y_));
                if (((int)x_) != 0) {
                    x_ -= (std::floor(x_));
                }
                if (((int)y_) != 0) {
                    y_ -= (std::floor(y_));
                }

                if (i == ((int)delay / 3)) {
                    x_ += getRecoilXRand(o);
                    y_ += getRecoilYRand(o);
                }
            }
        }
    }

    void genLinearInterpolation() {
        double delay = getRoundTime();
        double moveY = 0;
        double moveX = 0;
        for (int o = 0; o < setWeapon.recoilPattern.size(); o++)
        {
            double control_time = getControlTime(o);
            double dx = getRecoilXRand(o);
            double dy = getRecoilYRand(o);

            for (int i = 0; i < delay; i++) {
                if (i <= control_time) {
                    moveX += dx / control_time;
                    moveY += dy / control_time;
                }
                x.push_back((int)moveX);
                if (((int)moveX) != 0) {
                    moveX -= (int)(moveX);
                }
                y.push_back((int)moveY);
                if (((int)moveY) != 0) {
                    moveY -= (int)(moveY);
                }

            }

        }
    }
    void genSplineInterpolation(tk::spline::spline_type type) {
        std::vector<double> X_time = std::vector<double>();
        std::vector<double> Y_x = std::vector<double>();
        std::vector<double> Y_y = std::vector<double>();

        double roundTime = getRoundTime();

        // generate absolute values
        float totalX = 0;
        float totalY = 0;
        X_time.push_back(0);
        Y_x.push_back(0);
        Y_y.push_back(0);
        for (int o = 0; o < setWeapon.recoilPattern.size(); o++) {
            float dx = getRecoilXRand(o);
            float dy = getRecoilYRand(o);
            totalX += dx;
            totalY += dy;
            Y_x.push_back(totalX);
            Y_y.push_back(totalY);
            Y_x.push_back(totalX);
            Y_y.push_back(totalY);
            double time = (o + 1) * roundTime;
            X_time.push_back(time - roundTime / 10);
            X_time.push_back(time);


            //std::cout << "{"+to_string(o*roundTime) + "," + to_string(totalY)+"},";
        }
        //generate spline
        tk::spline splineX(X_time, Y_x, type);
        tk::spline splineY(X_time, Y_y, type);

        double lastX = 0;
        double lastY = 0;

        double scheduledX = 0;
        double scheduledY = 0;

        for (double o = 1; o < setWeapon.recoilPattern.size() * roundTime; o++) {
            double ax = splineX(o); // absolute X
            double ay = splineY(o); // absolute Y
            double relX = (ax - lastX); // calculate relative X
            double relY = (ay - lastY); // calculate relative Y
            scheduledX += relX;
            scheduledY += relY;
            //std::cout << "  o: " + to_string(o) + " val: " + to_string(relX);
            lastY = ay;
            lastX = ax;
            if (abs(scheduledX) > 1) {
                x.push_back((int)scheduledX);
                scheduledX -= (int)scheduledX;
            }
            else {
                x.push_back(0);
            }
            if (abs(scheduledY) > 1) {
                y.push_back((int)scheduledY);
                scheduledY -= (int)scheduledY;
            }
            else {
                y.push_back(0);
            }

        }
    }

public:
    int count = 0;
    PatternGenerator(Settings s) {
        this->setWeapon = GameData::weapons.at(s.getCurrentWeapon());
        this->setScope = GameData::scopes.at(s.getCurrentScope());
        this->playerFOV = s.getIngameFOV();
        this->playerSens = s.getPlayerSens();
        this->weapon_inaccuracy = s.getCurrentInaccuracy();
    }
    void update(Settings s) {
        this->setWeapon = GameData::weapons.at(s.getCurrentWeapon());
        this->setScope = GameData::scopes.at(s.getCurrentScope());
        this->playerFOV = s.getIngameFOV();
        this->playerSens = s.getPlayerSens();
        this->weapon_inaccuracy = s.getCurrentInaccuracy();
    }

    // generated vals
    ::std::vector<int> x;
    ::std::vector<int> y;

    // paint vals
    double totalX = 0;
    double totalY = 0;
    double totalTime = 0;
    int maxX = 0;
    int minX = 0;
    int maxY = 0;
    int minY = 0;
    std::vector<int> x_;
    std::vector<int> y_;

    System::Drawing::Pen^ getPenRed(int thicc) {
        System::Drawing::Pen^ p = gcnew System::Drawing::Pen(System::Drawing::Color::Red);
        p->Width = thicc;
        return p;
    }
    System::Drawing::Pen^ getPenBlack(int thicc) {
        System::Drawing::Pen^ p = gcnew System::Drawing::Pen(System::Drawing::Color::Black);
        p->Width = thicc;
        return p;
    }
    void gen(int mode) {
        x.clear();
        y.clear();
        recoilDiffX = 0;
        recoilDiffY = 0;
        switch (mode) {
        case 0:
            genLinearInterpolation();
            break;
        case 1:
            genSplineInterpolation(tk::spline::cspline);
            break;
        case 2:
            genSplineInterpolation(tk::spline::cspline_hermite);
            break;
        case 3:
            genWithoutInterpolation();
            break;
        }
        updatePaintVals();
    }

    void updatePaintVals() {
        x_.clear();
        y_.clear();
        totalX = 0;
        totalY = 0;
        totalTime = 0;
        maxX = 0;
        minX = 0;
        maxY = 0;
        minY = 0;

        for (int i = 0; i < getSetWeapon().recoilPattern.size(); i++) {
            x_.push_back((int)totalX);
            y_.push_back((int)totalY);
            totalX += getRecoilX(i);
            totalY += getRecoilY(i);
            totalTime += getSetWeapon().roundTime;
            if (totalX > maxX) maxX = totalX;
            if (totalX < minX) minX = totalX;
            if (totalY > maxY) maxY = totalY;
            if (totalY < minY) minY = totalY;
        }
    }

    double getRecoilX(int index) {
        return setWeapon.recoilPattern.at(index).x * setScope.multiplierRecoil * 0.25 * playerFOV / (90.0 * playerSens);
    }
    double getRecoilY(int index) {
        return setWeapon.recoilPattern.at(index).y * setScope.multiplierRecoil * 0.25 * playerFOV / (90.0 * playerSens);
    }
    double getControlTime(int index) {
        return setWeapon.controlTime.at(index);
    }
    double getRoundTime() {
        return setWeapon.roundTime;
    }

    int getGeneratedArrayLength() {
        return this->x.size();
    }
    weapon getSetWeapon() {
        return this->setWeapon;
    }
    void tickWeapon() {
        double x_ = 0;
        double y_ = 0;
        for (int i = count * setWeapon.recoilPattern.size(); i < (count + 1) * setWeapon.recoilPattern.size(); i++) {
            if (i >= x.size()) return;
            x_ += x.at(i) * ((setWeapon.affectedByCrouch && isCrouched) ? 0.5 : 1);;
            y_ += y.at(i) * ((setWeapon.affectedByCrouch && isCrouched) ? 0.5 : 1);

            if (!((int)x_ == 0 && (int)y_ == 0))mouse_event(1, x_, y_, 0, 0);
            if (((int)x_) != 0) {
                x_ -= (std::floor(x_));
            }
            if (((int)y_) != 0) {
                y_ -= (std::floor(y_));
            }
            sleep(1);
        }
        count++;
    }
    
};
static ref class FormHolder {
public:
    static RapidGUI::MyForm^ form;
    static void set(RapidGUI::MyForm^ f) {
        form = f;
    }
    ~FormHolder() {
        delete form;
    }
};

bool isRunning = true;




static Settings settings;
static PatternGenerator generator = PatternGenerator(settings);

void updateGUIParts() {



    FormHolder::form->selectedInterpolationBox->Text = gcnew System::String(StatesData::interpolationModes.at(::settings.getInterpolationType()).name.c_str());
    FormHolder::form->GunBox->Text = gcnew System::String(GameData::weapons.at(::settings.getCurrentWeapon()).name.c_str());
    FormHolder::form->ScopeBox->Text = gcnew System::String(GameData::scopes.at(::settings.getCurrentScope()).name.c_str());
    FormHolder::form->RandomPercentNumberBox->Value = (int)settings.getCurrentInaccuracy();

    if (settings.getRegeneratePerCycle()) {
        FormHolder::form->RegenerateBox->CheckState = System::Windows::Forms::CheckState::Checked;
    }


    

}


System::Void RapidGUI::MyForm::MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
    this->dragging = false;
};

System::Void RapidGUI::MyForm::MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
    //generator.updateRecoilDiagrams(this->SprayPatternBox, this->SprayFieldX, this->SprayFieldY);

}
System::Void RapidGUI::MyForm::MyForm_Shown(System::Object^ sender, System::EventArgs^ e) {
    //generator.updateRecoilDiagrams(this->SprayPatternBox, this->SprayFieldX, this->SprayFieldY);
}

System::Void RapidGUI::MyForm::RegenerateBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    settings.setRegeneratePerCycle(FormHolder::form->RegenerateBox->CheckState == System::Windows::Forms::CheckState::Checked);
}


System::Void RapidGUI::MyForm::SprayPatternBox_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
  
    System::Drawing::Graphics^ graphicsXY = e->Graphics;
    double paddingX = (e->ClipRectangle.Width / 4.0);
    double paddingY = (e->ClipRectangle.Height / 8.0);
    double localMaxX = generator.maxX;
    double localMaxY = generator.maxY;
    localMaxX += paddingX;
    localMaxY += paddingY;
    double factorXY_x = ((double)e->ClipRectangle.Width) / (double)(abs(generator.minX) + abs(localMaxX));
    double factorXY_y = ((double)e->ClipRectangle.Height) / (double)(abs(generator.minY) + abs(localMaxY));
    double factorXY = factorXY_x < factorXY_y ? factorXY_x : factorXY_y;
    double incXY_x = (generator.minX < 0 ? generator.minX * -1 : 0) + (paddingX/2.0);
    double incXY_y = (generator.minY < 0 ? generator.minY * -1 : 0) + (paddingY/2.0);
    for (int i = 0; i < generator.getSetWeapon().recoilPattern.size(); i++) {
        graphicsXY->DrawEllipse(generator.getPenRed(2), ((generator.x_.at(i) + incXY_x) * factorXY) -5 , ((generator.y_.at(i) + incXY_y) * factorXY) - 5, 10, 10);
    }
    int bX = 0;
    int bY = 0;
    for (int i = 0; i < generator.x.size(); i++) {
        bX += generator.x.at(i);
        bY += generator.y.at(i);
        if ((i/generator.getSetWeapon().roundTime) > generator.getSetWeapon().recoilPattern.size()) return;
        graphicsXY->DrawEllipse(generator.getPenBlack(2), (bX + incXY_x) * factorXY, (bY + incXY_y) * factorXY, 1, 1);
    }
}
System::Void RapidGUI::MyForm::SprayFieldX_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {

    System::Drawing::Graphics^ graphicsXY = e->Graphics;
    double paddingX = (e->ClipRectangle.Width / 2.0);
    double paddingY = (e->ClipRectangle.Height / 4.0);
    double localMaxX = generator.totalTime;
    double localMaxY = generator.maxY;
    localMaxX += paddingX;
    localMaxY += paddingY;
    double factorXY_x = ((double)e->ClipRectangle.Width) / (double)(localMaxX);
    double factorXY_y = ((double)e->ClipRectangle.Height) / (double)(abs(generator.minY) + abs(localMaxY));
    double factorXY = factorXY_x < factorXY_y ? factorXY_x : factorXY_y;
    double incXY_x = (paddingX / 2.0);
    double incXY_y = (generator.minY < 0 ? generator.minY * -1 : 0) + (paddingY / 2.0);
    for (int i = 0; i < generator.getSetWeapon().recoilPattern.size(); i++) {
        graphicsXY->DrawEllipse(generator.getPenRed(2), ((i*generator.getSetWeapon().roundTime + incXY_x) * factorXY) - 1, ((generator.y_.at(i) + incXY_y) * factorXY) - 1, 3, 3);
    }
    int bX = incXY_x;
    int bY = incXY_y;
    for (int i = 0; i < generator.x.size(); i++) {
        bX += 1;
        bY += generator.y.at(i);
        graphicsXY->DrawEllipse(generator.getPenBlack(2), (bX) * factorXY, (bY) * factorXY, 1, 1);
    }
}


System::Void RapidGUI::MyForm::SprayFieldY_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
    System::Drawing::Graphics^ graphicsXY = e->Graphics;
    double paddingX = (e->ClipRectangle.Width / 2.0);
    double paddingY = (e->ClipRectangle.Height / 4.0);
    double localMaxX = generator.totalTime;
    double localMaxY = generator.maxX;
    localMaxX += paddingX;
    localMaxY += paddingY;
    double factorXY_x = ((double)e->ClipRectangle.Width) / (double)(localMaxX);
    double factorXY_y = ((double)e->ClipRectangle.Height) / (double)(abs(generator.minX) + abs(localMaxY));
    double factorXY = factorXY_x < factorXY_y ? factorXY_x : factorXY_y;
    double incXY_x = (paddingX / 2.0);
    double incXY_y = (generator.minX < 0 ? generator.minX * -1 : 0) + (paddingY / 2.0);
    for (int i = 0; i < generator.getSetWeapon().recoilPattern.size(); i++) {
        graphicsXY->DrawEllipse(generator.getPenRed(2), ((i * generator.getSetWeapon().roundTime + incXY_x) * factorXY) - 1, ((generator.x_.at(i) + incXY_y) * factorXY) - 1, 3, 3);
    }
    int bX = incXY_x;
    int bY = incXY_y;
    for (int i = 0; i < generator.x.size(); i++) {
        bX += 1;
        bY += generator.x.at(i);
        graphicsXY->DrawEllipse(generator.getPenBlack(2), (bX)*factorXY, (bY)*factorXY, 1, 1);
    }
}


System::Void RapidGUI::MyForm::selectedInterpolationBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
    settings.setInterpolationType(FormHolder::form->selectedInterpolationBox->SelectedIndex);
    generator.gen(settings.getInterpolationType());
    FormHolder::form->repaintBoxes();
}
System::Void RapidGUI::MyForm::RandomPercentNumberBox_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
    settings.setInaccuracy((int)FormHolder::form->RandomPercentNumberBox->Value.ToInt32(FormHolder::form->RandomPercentNumberBox->Value));
    generator.update(settings);
    generator.gen(settings.getInterpolationType());
    FormHolder::form->repaintBoxes();
}

System::Void RapidGUI::MyForm::GunBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
    settings.setCurrentWeapon(FormHolder::form->GunBox->SelectedIndex);
    updateGUIParts();
    generator.update(settings);
    generator.gen(settings.getInterpolationType());
    FormHolder::form->repaintBoxes();
}
System::Void RapidGUI::MyForm::ScopeBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
    settings.setCurrentScope(FormHolder::form->ScopeBox->SelectedIndex);
    generator.update(settings);
    generator.gen(settings.getInterpolationType());
    FormHolder::form->repaintBoxes();
}
bool isWindowHidden = false;
bool isEnabled = false;
void rapidBackend() {
    generator.gen(settings.getInterpolationType());
    while (isRunning)
    {
        if (isEnabled) {
            if ((GetAsyncKeyState(VK_LBUTTON) && (GetAsyncKeyState(VK_RBUTTON)))) generator.tickWeapon();
            else
            {
                if (generator.count != 0) {
                    if (settings.getRegeneratePerCycle()) {
                        generator.gen(settings.getInterpolationType());
                        FormHolder::form->repaintBoxes();
                    }
                }
                generator.count = 0;
            }
        }
        
        if (GetAsyncKeyState(VK_RSHIFT) == -32767) {
            isWindowHidden = !isWindowHidden;
            if (isWindowHidden) {
                ::ShowWindow((HWND)FormHolder::form->Handle.ToInt32(), SW_HIDE);
            }
            else {
                ::ShowWindow((HWND)FormHolder::form->Handle.ToInt32(), SW_SHOW);
            }
        }
        if (GetAsyncKeyState(VK_DELETE) == -32767) {
            isEnabled = !isEnabled;
            if (isEnabled) {
                FormHolder::form->enabledBox->CheckState = System::Windows::Forms::CheckState::Checked;
            }
            else {
                FormHolder::form->enabledBox->CheckState = System::Windows::Forms::CheckState::Unchecked;
            }
        }
        if (generator.getSetWeapon().affectedByCrouch) {
            isCrouched = GetAsyncKeyState(VK_LCONTROL);
        }
        

    }
}


[STAThread]
void main(array<String^>^ arg) {
    srand(time(NULL));
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    RapidGUI::MyForm form;
    FormHolder::set(% form);
    for (weapon w : GameData::weapons) {
        FormHolder::form->GunBox->Items->Add(gcnew String(w.name.c_str()));
    }
    for (scope s : GameData::scopes) {
        FormHolder::form->ScopeBox->Items->Add(gcnew String(s.name.c_str()));
    }
    for (InterpolationMode s : StatesData::interpolationModes) {
        FormHolder::form->selectedInterpolationBox->Items->Add(gcnew String(s.name.c_str()));
    }

    updateGUIParts();
    std::thread rapid(rapidBackend);
    Application::Run(% form);
    isRunning = false;
    rapid.join();
    
}