const double EPS = 1E-8;
typedef vector<double> vec;
typedef vector <vec> mat;

//Ax = b を解く。Aは正方行列
// 解がないか、一意でない場合は長さ0の配列を返す
vec gauss_jordan(const mat &A, const vec &b) {
    int n = A.size();
    mat B(n, vec(n + 1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) B[i][j] = A[i][j];
    //行列Aの後ろにbを並べ、同時に処理する。
    for (int i = 0; i < n; i++) B[i][n] = b[i];

    for (int i = 0; i < n; i++) {
        //注目している変数の係数の絶対値が大きい式をi番目に持ってくる
        int pivot = i;
        for (int j = i; j < n; j++) {
            if (abs(B[j][i]) > abs(B[pivot][i])) pivot = j;
        }
        swap(B[i], B[pivot]);

        //解がないか一意でない
        if (abs(B[i][i]) < EPS) return vec();

        //注目している変数の係数を1にする
        for (int j = i + 1; j <= n; j++) B[i][j] /= B[i][i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                //j番目の式からi番目の変数を削除
                for (int k = i + 1; k <= n; k++) B[j][k] -= B[j][i] * B[i][k];
            }
        }
    }
    vec x(n);
    for (int i = 0; i < n; i++) x[i] = B[i][n];
    return x;
}