struct Point{
	int x, y;
	Point(int x = 0, int y = 0) : x(x), y(y) {}
};

// Ax + By = C
struct Line { 
    double a, b, c;
    Line(double a = 0.0, double b = 0.0, double c = 0.0) : a(a), b(b), c(c) {}
};

// Tích có hướng của AB và AC
long long Cross(const Point &A, const Point &B, const Point &C) {
    return 1LL * (B.x - A.x) * (C.y - A.y) - 1LL * (C.x - A.x) * (B.y - A.y);
}

// Tích vô hướng của AB và AC
long long Dot(const Point &A, const Point &B, const Point &C) {
    return 1LL * (B.x - A.x) * (C.x - A.x) + 1LL * (B.y - A.y) * (C.y - A.y);
}

// C nằm trên đoạn AB nếu AB * AC = 0 và CA.CB <= 0
bool onSegment(const Point &A, const Point &B, const Point &C) {
    return Cross(A, B, C) == 0 && Dot(C, A, B) <= 0;
}

double Sqr(int x){
	return (double)1LL*x*x;
}

// Khoảng cách giữa hai tạo độ
double Dist(const Point &A, const Point &B){
	return (double)sqrt(Sqr(B.x - A.x) + Sqr(B.y - A.y));
}

// Tìm giao điểm của hai đường thẳng d1 và d2
pair <double, double> GiaoDiem(const Line &d1, const Line &d2){
	double det = 1LL* d1.a * d2.b - 1LL * d2.a * d1.b;
	double x, y;
	if (det == 0){
	    if (1LL * d1.a * d2.c == 1LL * d2.a * d1.c) cout << "Hai duong thang trung nhau";
	    else cout << "Hai duong thang song song";
	}
	else{
	    x = (1LL * d2.b * d1.c - 1LL * d1.b * d2.c) / det;
	    y = (1LL * d1.a * d2.c - 1LL * d2.a * d1.c) / det;
	}
	
	return {x, y};
}

// Tìm tọa độ đối xứng của điểm (X, Y) qua trục d
pair <double, double> Symmetry(const Point &X, const Line &d) {
    // Phương trình đường vuông góc có dạng: -Bx + Ay = D
    double D = -d.b * X.x + d.a * X.y;
    Line d2 = Line(-d.b, d.a, D);
    pair <double, double> Y = GiaoDiem(d, d2);
    pair <double, double> X2 = {2 * Y.first - X.x, 2 * Y.second - X.y};
    return X2;
}

// Khoảng cách nhỏ nhất từ một tọa độ (X, Y) = (P[0].x, P[0].y) đến một đa giác
double MinDist(const vector <Point> &P){
	int N = (int)P.size();
	double ans = 1e9;
	for (int i = 1; i < N; i++)
		for (int j = i + 1; j < N; j++){
			// Vector i -> j = AB
			int Ax = P[j].x - P[i].x;
			int Ay = P[j].y - P[i].y;

			// Vector (X, Y) -> i = AP
			int Bx = P[0].x - P[i].x;
			int By = P[0].y - P[i].y;

			// Tích có hướng của AP.AB = Ax*Bx + Ay*By
			int Mul = Ax*Bx + Ay*By;

			// Độ dài bình phương AB = Ax^2 + Ay^2
			int lenSqr = Ax*Ax + Ay*Ay;

			// Tham số t = (AP.AB)/|AB^2|
			double t = Mul*1.0/lenSqr; 

			/*
				t <= 0 --> Khoảng cách gần nhất là A
				t >= 1 --> Khoảng cách gần nhất là B
				0 < 1 < t --> Khoảng cách gần nhất là hình chiếu P lên AB
			*/
			if (t <= 0.0) ans = min(ans, Dist(P[0], P[i]));
			else
				if (t >= 1.0) ans = min(ans, Dist(P[0], P[j]));
				else{
					/*	
						Vector chỉ phương AB = (xB - xA; yB - yA)
						--> Vector pháp tuyến = (-yB + yA; xB - xA) = (a; b)
						--> Phương trình tổng quát: a(x - xP) + b(y - yP) = 0
							--> ax - axP + by - byP = 0
							--> ax + by - axP - byP = 0
						d(P, AB) = abs(a*xP + b*yP + c)/Sqrt(a*a + b*b)
					*/
					int a = -P[j].y + P[i].y; 
					int b = P[j].x - P[i].x;
					int c = -a*P[i].x - b*P[i].y;
					double k = 1.0*a*P[0].x + b*P[0].y + c; 
					if (k < 0.0) k *= -1.0;
					ans = min(ans, (double)k/(1.0*sqrt(a*a + b*b)));
				}
		}

	return ans;
}

// Tính diện tích của đa giác
long long Area(const vector<Point> &P) {
    int n = P.size();
    long long ans = 0;

    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        ans += 1LL * P[i].x * P[j].y;
        ans -= 1LL * P[j].x * P[i].y;
    }

    // vector <Point> A = P;
    // A.push_back(P.front());
    // long long ans = 0;
    // for (int i = 0; i < (int)A.size() - 1; i++) ans += 1LL * (A[i + 1].x - A[i].x) * (A[i + 1].y + A[i].y);
    
    return abs(ans) / 2.0;
}



// Tìm bao lồi (Cross > 0 thì lấy cả những tọa độ trên biên còn không Cross >= 0 thì không lấy)
vector <Point> ConvexHull(vector <Point> &P){
	int n = (int)P.size();
	sort(begin(P), end(P), [&](const Point &A, const Point &B){
		return (A.x == B.x ? A.y < B.y : A.x < B.x);
	});

	vector <Point> Up, Down;
	for (int i = 0; i < n; i++){
		while ((int)Up.size() >= 2 && Cross(Up[(int)Up.size() - 2], Up.back(), P[i]) >= 0.0) Up.pop_back();
		Up.push_back(P[i]);
	}
	for (int i = n - 1; i >= 0; i--){
		while ((int)Down.size() >= 2 && Cross(Down[(int)Down.size() - 2], Down.back(), P[i]) >= 0.0) Down.pop_back();
		Down.push_back(P[i]);
	}

	Down.pop_back();
	Down.erase(Down.begin());

	vector <Point> hull;
	for (auto &p: Up) hull.push_back(p);
	for (auto &p: Down) hull.push_back(p);
	
	return hull;
}
