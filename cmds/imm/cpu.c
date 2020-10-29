inherit F_CLEAN_UP;
int main(object me)
{
        mapping info;
        float x, fraction,fraction2;
        string str;

        if (! SECURITY_D->valid_grant(me, "(immortal)")) 
                return 0; 
        info = rusage();
        x = info["utime"] + info["stime"];

        x = info["stime"]/10;
        fraction = x / uptime();
        x = info["utime"]/10;
        fraction2 = x / uptime();
        str = sprintf("CPU usage -- Sys: %2.2f -- User: %2.2f\n", fraction,fraction2);
        write( str );
        return 1;
}
