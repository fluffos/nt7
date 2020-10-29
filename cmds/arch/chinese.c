// chinese.c

inherit F_CLEAN_UP;

int help();

int main(object me, string arg)
{
        string key, chinz;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (! arg || arg == "" )
        {
                help();
                return 1;
        }

        if (sscanf(arg, "-d %s", key))
        {
                CHINESE_D->remove_translate(key);
                write(sprintf("Remove %s.\n", key));
                return 1;
        }

        if (sscanf(arg, "%s==%s", key, chinz) == 2)
        {
                CHINESE_D->add_translate(key, chinz);
                write(key + " == " + chinz + "\nOk.\n");
                return 1;
        } else
        {
                write(sprintf("Now translate %s to %s.\n",
                      arg, to_chinese(arg)));
        }

        return 1;
}

int help()
{
        write(@HELP
指令格式：chinese <英文>==<中文> 或
          chinese -d <英文>
HELP );
        return 1 ;
}