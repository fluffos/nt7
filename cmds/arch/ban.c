// ban.c
// Created by Xiang@XKX

int help(object me);

void create()
{
        seteuid(getuid());
}

int main(object me, string arg)
{
        string site;
        
        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        BAN_D->load_sites();
        
        if (! arg) write(BAN_D->list_sites());
        else if (sscanf(arg, "+ %s", site) == 1)
                BAN_D->add_site(site);
        else if (sscanf(arg, "- %s", site) == 1)
                BAN_D->remove_site(site);
        else if (sscanf(arg, "add %s", site) == 1)
                BAN_D->add_welcome_user(site);
        else if (sscanf(arg, "del %s", site) == 1)
                BAN_D->remove_welcome_user(site);
        else if (sscanf(arg, "list %s", site) == 1)
        {
                if (site == "wel") write(BAN_D->list_welcome_users());
                else if (site == "net") BAN_D->list_netclubs();
        }
        else return help(me);

        return 1;
        
}

int help(object me)
{
        write(@HELP
指令格式：ban [+|- site]
          ban [add|del id]
          ban [list wel|net]

这条命令是用来防止有人蓄意捣乱。
HELP
        );
        return 1;
}


