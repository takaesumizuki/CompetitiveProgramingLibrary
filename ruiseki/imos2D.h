template <typename T>
class Imos2d{
    vector<vector<T> > vv;
    unsigned xSize{};
    unsigned ySize{};
public:
    Imos2d(unsigned xSize, unsigned ySize){
        vector<vector<T> > vv(xSize + 2, vector<T> (ySize + 2));
        this->vv = vv;
        this->xSize = xSize + 2;
        this->ySize = ySize + 2;
    }
    //[sx,tx),[sy,ty)の範囲をvalueで埋める
    void add(int sx,int sy,int tx,int ty,T value){
        sx++;
        sy++;
        tx++;
        ty++;
        this->vv[sx][sy] += value;
        this->vv[tx][ty] += value;
        this->vv[sx][ty] -= value;
        this->vv[tx][sy] -= value;
    }
    void set_sum(){
        for(int i = 0; i < xSize - 1; i++){
            for(int j = 0; j < ySize; j++){
                this->vv[i+1][j] += vv[i][j];
            }
        }
        for(int i = 0; i < xSize; i++){
            for(int j = 0; j < ySize - 1; j++){
                this->vv[i][j+1] += vv[i][j];
            }
        }
    }
    T calc(int x,int y){

        return this->vv[x+1][y+1];
    }
};