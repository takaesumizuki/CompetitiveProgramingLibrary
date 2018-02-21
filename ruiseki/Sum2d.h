/**
 * 注意
 * 内部では1-indexだが外からは0-indexで操作してね★
 */
template <typename T>
class Sum2d{
    vector<vector<T> > vv;
    unsigned xSize{};
    unsigned ySize{};
public:
    Sum2d(unsigned xSize, unsigned ySize){
        vector<vector<T> > vv(xSize + 2, vector<T> (ySize + 2));
        this->vv = vv;
        this->xSize = xSize + 2;
        this->ySize = ySize + 2;
    }
    void add(int x,int y,T value){
        x++;
        y++;
        this->vv[x][y] += value;
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
    //[sx,tx],[sy,ty]の範囲を求めるZE
    T calc(int sx,int sy,int tx,int ty){
        tx++;
        ty++;
        return this->vv[tx][ty] + this->vv[sx][sy] - this->vv[tx][sy] - this->vv[sx][ty];
    }
};