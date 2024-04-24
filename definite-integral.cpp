
#include <iostream>
#include <time.h>
#include <random>
#include <unistd.h>
using namespace std;

//定積分は面積を求める計算　　　I = (b-a) * h * (領域内の点の数/すべての点の数)
void decide_abh(double *a, double *b, double *h) {
	cout << "a, b, h の値を決定します。(0 < a < b),(0 < h)"<< endl;
  
	cout << "a の値を入力してください。"<< endl;
	cin >> *a;
	if (*a <= 0) {
		do {
		  cout << "a の値の条件を確認して、もう一度入力してください。" << endl;
		  cin >> *a;
		} while (*a <= 0);
	}
  
	cout << "b の値を入力してください。"<< endl;
	cin >> *b;	
	if (*b <= *a) {
		do {
		  cout << "b の値の条件を確認して、もう一度入力してください。" << endl;
		  cin >> *b;
			} while (*b <= *a);
	}
  
	cout << "h の値を入力してください。"<< endl;
	cin >> *h;	
		if (*h <= 0) {
		do {
		  cout << "h の値の条件を確認して、もう一度入力してください。" << endl;
		  cin >> *h;
		} while (*h <= 0);
	}
  
  cout << "a = " << *a << ", b = " << *b << ", h = " << *h << " となりました。" << endl << endl;	
}

bool inarea_ornot(double x, double y) {	
  return 3 * pow(x,2) + 3 * x + 2 >= y; // y=3x^2+3x+2の積分
}

uint32_t get_seed() {
  time_t now = time(NULL);
  tm* localTime = localtime(&now);
  return (localTime->tm_hour * 60 + localTime->tm_min) * 60 + localTime->tm_sec;	
}

int main() {
	const int l = 10000000; // 試行回数　
	cout << "y=3x^2+3x+2の積分を行います。" << endl;

	//a, b, h の入力を求める
	double a, b, h; //入力値
  decide_abh(&a, &b, &h);

	// 乱数エンジンにseed設定用クラス
  mt19937_64 random_engine;
  random_engine = mt19937_64(get_seed());
  
  // 範囲指定	
	uniform_real_distribution <> dist_x, dist_y;
  dist_x = uniform_real_distribution <> (a, b);
  dist_y = uniform_real_distribution <> (0, h);

	//時間がかかるので待ってもらう　面白いコードを借りてきた...	
	int count = 0; 
  fprintf(stderr, "0%%       50%%       100%%\n"); 
  fprintf(stderr, "+---------+---------+\n");
  for (int i = 0; i <= 100; i++) {
    for (int j = 0; j < i / 5 + 1; j++) {
      fprintf(stderr, "#");
    }
    fprintf(stderr, "\n");
    fprintf(stderr, "%3d%%\n", i);
    // l/100回繰り返すことを100回繰り返すからl回になる
    for (int k = 0; k < l / 100; k++) {
      count += inarea_ornot(dist_x(random_engine), dist_y(random_engine));
		}
    fprintf(stderr, "\033[2A");
	}
	
	double I = (b-a) * h * ((double)count / (double)l);
	cout << endl << endl;
	cout << "積分値 I = " << I << endl;	
  return 0;
}
