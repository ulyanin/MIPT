BEGIN { last=""; count=0 } 
{
    if (last!=$1) {
        if (count) {
            print last " " count
        };
        last=$1; 
        count=0
    } 
    { count++;} 
} 
END { 
    if (count!=0) {
        print last " " count
    } 
}
