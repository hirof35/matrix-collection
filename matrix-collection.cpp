#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstring>
#include <string>   // 文字列クラスで安全に処理
using namespace std;

// ============== プロトタイプ宣言 ==============
void display2D(double m[2][2]);
void display3D(double m[3][3]);
void display3Daug(double m[3][4]);
double det2D(double m[2][2]);
double det3D(double m[3][3]);
void trans2D(double m[2][2], double r[2][2]);
void trans3D(double m[3][3], double r[3][3]);
void add2D(double a[2][2], double b[2][2], double r[2][2]);
void sub2D(double a[2][2], double b[2][2], double r[2][2]);
void mul2D(double a[2][2], double b[2][2], double r[2][2]);
void add3D(double a[3][3], double b[3][3], double r[3][3]);
void sub3D(double a[3][3], double b[3][3], double r[3][3]);
void mul3D(double a[3][3], double b[3][3], double r[3][3]);
int rank2D(double m[2][2]);
int rank3D(double m[3][3]);
int inv2D(double m[2][2], double r[2][2]);
int inv3D(double m[3][3], double r[3][3]);
int solve3x3(double aug[3][4], double x[3]);
int solve2x2(double aug[2][3], double x[2]);

// ★ 改善：stringを使用し安全にファイル処理
int saveFile3D(double m[3][3], string filename);
int loadFile3D(double m[3][3], string filename);
int saveFile2D(double m[2][2], string filename);
int loadFile2D(double m[2][2], string filename);
// ===============================================


// ============== メイン ==============
int main() {
    int dim, op;
    string filename;
    cout << "===== 行列計算プログラム =====" << endl;
    cout << "1. 2×2 行列 / 2元連立方程式" << endl;
    cout << "2. 3×3 行列 / 3元連立方程式" << endl;
    cout << "次元を選択：";
    cin >> dim;

    if(dim == 1) {
        double A[2][2], B[2][2], R[2][2];
        cout << "\n--- 行列A入力 ---" << endl;
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++){
                cout << "A["<<i+1<<"]["<<j+1<<"]="; cin >> A[i][j];
            }
        cout << "\n--- 行列B入力（加減算・積で使用）---" << endl;
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++){
                cout << "B["<<i+1<<"]["<<j+1<<"]="; cin >> B[i][j];
            }

        do {
            cout << "\n===== 2×2 メニュー =====" << endl;
            cout << " 1. 加算 A+B" << endl;
            cout << " 2. 減算 A-B" << endl;
            cout << " 3. 積 A×B" << endl;
            cout << " 4. 行列式 |A|" << endl;
            cout << " 5. 転置 Aᵀ" << endl;
            cout << " 6. 逆行列 A⁻¹" << endl;
            cout << " 7. 階数 rank(A)" << endl;
            cout << " 8. 2元連立方程式 A·x=b を解く" << endl;
            cout << " 9. 行列Aをファイル保存（例: data2.txt）" << endl;
            cout << "10. ファイルから読込" << endl;
            cout << " 0. 終了" << endl;
            cout << "選択："; cin >> op;
            if(op==0) break;
            double aug2[2][3], x2[2];
            int ret;

            switch(op) {
                case 1: add2D(A,B,R); cout << "\n👉 A+B：\n"; display2D(R); break;
                case 2: sub2D(A,B,R); cout << "\n👉 A-B：\n"; display2D(R); break;
                case 3: mul2D(A,B,R); cout << "\n👉 A×B：\n"; display2D(R); break;
                case 4: cout << "\n👉 |A| = " << det2D(A) << endl; break;
                case 5: trans2D(A,R); cout << "\n👉 Aᵀ：\n"; display2D(R); break;
                case 6:
                    ret = inv2D(A,R);
                    if(ret<0) cout << "⚠ 逆行列が存在しません（行列式=0）" << endl;
                    else { cout << "\n👉 A⁻¹：\n"; display2D(R); }
                    break;
                case 7: cout << "\n👉 rank(A) = " << rank2D(A) << endl; break;
                case 8:
                    cout << "右辺bの値を入力：" << endl;
                    for(int i=0;i<2;i++){
                        for(int j=0;j<2;j++) aug2[i][j] = A[i][j];
                        cout << "b["<<i+1<<"]="; cin >> aug2[i][2];
                    }
                    ret = solve2x2(aug2, x2);
                    if(ret<0) cout << "⚠ 解が一意に存在しません" << endl;
                    else cout << "👉 解：x1="<<x2[0]<<"  x2="<<x2[1]<<endl;
                    break;
                case 9:
                    cout << "ファイル名を入力（例: data2.txt）：";
                    cin >> filename;
                    saveFile2D(A, filename);
                    break;
                case 10:
                    cout << "読み込むファイル名：";
                    cin >> filename;
                    if(loadFile2D(A, filename)==0) { cout << "👉 読み込んだ行列：\n"; display2D(A); }
                    break;
                default: cout << "無効な選択です" << endl;
            }
        } while(true);
    }
    else if(dim == 2) {
        double A[3][3], B[3][3], R[3][3];
        cout << "\n--- 行列A入力 ---" << endl;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++){
                cout << "A["<<i+1<<"]["<<j+1<<"]="; cin >> A[i][j];
            }
        cout << "\n--- 行列B入力 ---" << endl;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++){
                cout << "B["<<i+1<<"]["<<j+1<<"]="; cin >> B[i][j];
            }

        do {
            cout << "\n===== 3×3 メニュー =====" << endl;
            cout << " 1. 加算 A+B" << endl;
            cout << " 2. 減算 A-B" << endl;
            cout << " 3. 積 A×B" << endl;
            cout << " 4. 行列式 |A|" << endl;
            cout << " 5. 転置 Aᵀ" << endl;
            cout << " 6. 逆行列 A⁻¹" << endl;
            cout << " 7. 階数 rank(A)" << endl;
            cout << " 8. 3元連立方程式 A·x=b を解く" << endl;
            cout << " 9. 行列Aをファイル保存（例: data3.txt）" << endl;
            cout << "10. ファイルから読込" << endl;
            cout << " 0. 終了" << endl;
            cout << "選択："; cin >> op;
            if(op==0) break;
            string filename;
            double aug3[3][4], x3[3];
            int ret;

            switch(op) {
                case 1: add3D(A,B,R); cout << "\n👉 A+B：\n"; display3D(R); break;
                case 2: sub3D(A,B,R); cout << "\n👉 A-B：\n"; display3D(R); break;
                case 3: mul3D(A,B,R); cout << "\n👉 A×B：\n"; display3D(R); break;
                case 4: cout << "\n👉 |A| = " << det3D(A) << endl; break;
                case 5: trans3D(A,R); cout << "\n👉 Aᵀ：\n"; display3D(R); break;
                case 6:
                    ret = inv3D(A,R);
                    if(ret<0) cout << "⚠ 逆行列が存在しません（行列式=0）" << endl;
                    else { cout << "\n👉 A⁻¹：\n"; display3D(R); }
                    break;
                case 7: cout << "\n👉 rank(A) = " << rank3D(A) << endl; break;
                case 8:
                    cout << "右辺bの値を入力：" << endl;
                    for(int i=0;i<3;i++){
                        for(int j=0;j<3;j++) aug3[i][j] = A[i][j];
                        cout << "b["<<i+1<<"]="; cin >> aug3[i][3];
                    }
                    cout << "\n👉 拡大係数行列：\n"; display3Daug(aug3);
                    ret = solve3x3(aug3, x3);
                    if(ret<0) cout << "⚠ 解が一意に存在しません" << endl;
                    else cout << "👉 解：x1="<<x3[0]<<"  x2="<<x3[1]<<"  x3="<<x3[2]<<endl;
                    break;
                case 9:
                    cout << "ファイル名を入力（例: data3.txt）：";
                    cin >> filename;
                    saveFile3D(A, filename);
                    break;
                case 10:
                    cout << "読み込むファイル名：";
                    cin >> filename;
                    if(loadFile3D(A, filename)==0) { cout << "👉 読み込んだ行列：\n"; display3D(A); }
                    break;
                default: cout << "無効な選択です" << endl;
            }
        } while(true);
    }
    cout << "\n終了しました。" << endl;
    return 0;
}
// ------ 表示関数（省略、前回と同じ）------
void display2D(double m[2][2]) {
    for (int i = 0; i < 2; i++) {
        cout << "│";
        for (int j = 0; j < 2; j++)
            cout << setw(10) << fixed << setprecision(4) << m[i][j];
        cout << " │" << endl;
    }
}

void display3D(double m[3][3]) {
    for (int i = 0; i < 3; i++) {
        cout << "│";
        for (int j = 0; j < 3; j++)
            cout << setw(10) << fixed << setprecision(4) << m[i][j];
        cout << " │" << endl;
    }
}

void display3Daug(double m[3][4]) {
    for (int i = 0; i < 3; i++) {
        cout << "│";
        for (int j = 0; j < 3; j++)
            cout << setw(10) << fixed << setprecision(4) << m[i][j];
        cout << " │" << setw(10) << fixed << setprecision(4) << m[i][3] << endl;
    }
}

double det2D(double m[2][2]) {
    return m[0][0]*m[1][1] - m[0][1]*m[1][0];
}

double det3D(double m[3][3]) {
    return m[0][0]*(m[1][1]*m[2][2]-m[1][2]*m[2][1])
         - m[0][1]*(m[1][0]*m[2][2]-m[1][2]*m[2][0])
         + m[0][2]*(m[1][0]*m[2][1]-m[1][1]*m[2][0]);
}

void trans2D(double m[2][2], double r[2][2]) {
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            r[j][i] = m[i][j];
}

void trans3D(double m[3][3], double r[3][3]) {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            r[j][i] = m[i][j];
}

void add2D(double a[2][2], double b[2][2], double r[2][2]) {
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            r[i][j] = a[i][j] + b[i][j];
}

void sub2D(double a[2][2], double b[2][2], double r[2][2]) {
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            r[i][j] = a[i][j] - b[i][j];
}

void mul2D(double a[2][2], double b[2][2], double r[2][2]) {
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            r[i][j]=0;
            for(int k=0;k<2;k++)
                r[i][j] += a[i][k] * b[k][j];
        }
    }
}

void add3D(double a[3][3], double b[3][3], double r[3][3]) {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            r[i][j] = a[i][j] + b[i][j];
}

void sub3D(double a[3][3], double b[3][3], double r[3][3]) {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            r[i][j] = a[i][j] - b[i][j];
}

void mul3D(double a[3][3], double b[3][3], double r[3][3]) {
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            r[i][j]=0;
            for(int k=0;k<3;k++)
                r[i][j] += a[i][k] * b[k][j];
        }
    }
}

int rank2D(double m[2][2]) {
    double d = det2D(m);
    if(fabs(d) > 1e-9) return 2;
    if(fabs(m[0][0])>1e-9 || fabs(m[0][1])>1e-9 ||
       fabs(m[1][0])>1e-9 || fabs(m[1][1])>1e-9) return 1;
    return 0;
}

int rank3D(double m[3][3]) {
    double d = det3D(m);
    if(fabs(d) > 1e-9) return 3;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(fabs(m[i][j]) > 1e-9) return 2;
    return 0;
}

int inv2D(double m[2][2], double r[2][2]) {
    double d = det2D(m);
    if(fabs(d) < 1e-9) return -1;
    r[0][0] =  m[1][1]/d;
    r[0][1] = -m[0][1]/d;
    r[1][0] = -m[1][0]/d;
    r[1][1] =  m[0][0]/d;
    return 0;
}

int inv3D(double m[3][3], double r[3][3]) {
    double d = det3D(m);
    if(fabs(d) < 1e-9) return -1;
    double c[3][3] = {
        { m[1][1]*m[2][2]-m[1][2]*m[2][1], -(m[1][0]*m[2][2]-m[1][2]*m[2][0]),  m[1][0]*m[2][1]-m[1][1]*m[2][0] },
        { -(m[0][1]*m[2][2]-m[0][2]*m[2][1]), m[0][0]*m[2][2]-m[0][2]*m[2][0], -(m[0][0]*m[2][1]-m[0][1]*m[2][0]) },
        { m[0][1]*m[1][2]-m[0][2]*m[1][1], -(m[0][0]*m[1][2]-m[0][2]*m[1][0]), m[0][0]*m[1][1]-m[0][1]*m[1][1] }
    };
    trans3D(c, r);
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            r[i][j] /= d;
    return 0;
}

int solve2x2(double aug[2][3], double x[2]) {
    double m[2][2] = {{aug[0][0],aug[0][1]},{aug[1][0],aug[1][1]}};
    double d = det2D(m);
    if(fabs(d) < 1e-9) return -1;
    x[0] = (aug[0][2]*m[1][1] - m[0][1]*aug[1][2]) / d;
    x[1] = (m[0][0]*aug[1][2] - aug[0][2]*m[1][0]) / d;
    return 0;
}

int solve3x3(double aug[3][4], double x[3]) {
    double a[3][4];
    memcpy(a, aug, sizeof(a));
    const double eps = 1e-9;
    for(int c=0;c<2;c++){
        int pivot = c;
        for(int r=c;r<3;r++)
            if(fabs(a[r][c]) > fabs(a[pivot][c])) pivot = r;
        for(int cc=c;cc<4;cc++){
            double t = a[c][cc]; a[c][cc] = a[pivot][cc]; a[pivot][cc] = t;
        }
        if(fabs(a[c][c]) < eps) return -1;
        for(int r=c+1;r<3;r++){
            double f = a[r][c]/a[c][c];
            for(int cc=c;cc<4;cc++)
                a[r][cc] -= f * a[c][cc];
        }
    }
    if(fabs(a[2][2]) < eps) return -1;
    for(int r=2;r>=0;r--){
        double s=a[r][3];
        for(int c=r+1;c<3;c++) s -= a[r][c]*x[c];
        x[r] = s / a[r][r];
    }
    return 0;
}

// ============== ★ 改善版：ファイル入出力 ==============
int saveFile2D(double m[2][2], string filename) {
    ofstream f(filename.c_str());
    if(!f.is_open()) {
        cout << "❌ エラー：ファイル「" << filename << "」を開けません" << endl;
        cout << "   ・ファイル名に日本語やスペースを使っていませんか？" << endl;
        cout << "   ・書き込み権限のあるフォルダで実行していますか？" << endl;
        return -1;
    }
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++)
            f << m[i][j] << " ";
        f << "\n";
    }
    f.close();
    if(!f.good()) {
        cout << "❌ 書き込み中にエラーが発生しました" << endl;
        return -2;
    }
    cout << "✅ 保存完了 → 「" << filename << "」" << endl;
    return 0;
}

int loadFile2D(double m[2][2], string filename) {
    ifstream f(filename.c_str());
    if(!f.is_open()) {
        cout << "❌ エラー：ファイル「" << filename << "」が見つかりません" << endl;
        return -1;
    }
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            f >> m[i][j];
    f.close();
    cout << "✅ 読込完了 → 「" << filename << "」" << endl;
    return 0;
}

int saveFile3D(double m[3][3], string filename) {
    ofstream f(filename.c_str());
    if(!f.is_open()) {
        cout << "❌ エラー：ファイル「" << filename << "」を開けません" << endl;
        cout << "   ・ファイル名に日本語やスペースを使っていませんか？" << endl;
        cout << "   ・書き込み権限のあるフォルダで実行していますか？" << endl;
        return -1;
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
            f << m[i][j] << " ";
        f << "\n";
    }
    f.close();
    if(!f.good()) {
        cout << "❌ 書き込み中にエラーが発生しました" << endl;
        return -2;
    }
    cout << "✅ 保存完了 → 「" << filename << "」" << endl;
    return 0;
}

int loadFile3D(double m[3][3], string filename) {
    ifstream f(filename.c_str());
    if(!f.is_open()) {
        cout << "❌ エラー：ファイル「" << filename << "」が見つかりません" << endl;
        return -1;
    }
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            f >> m[i][j];
    f.close();
    cout << "✅ 読込完了 → 「" << filename << "」" << endl;
    return 0;
}

