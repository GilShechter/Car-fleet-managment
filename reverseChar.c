
unsigned char reverse_char(unsigned char c){
    unsigned char x = 1, new=0;
    int i=0;
    for(;x>0;x <<= 1){
        new |= ( x & c ) << (sizeof(char) - 1 - i);
    }
    return new;
}

int main(){
    unsigned char c = 83;
    printf("%d", reverse_char(c) );
    return 0;
}