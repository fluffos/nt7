// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m凤舞九条[2;37;0m[2;37;0m", ({"piple"}));        
        set("gender", "女性");                
        set("long", "凤舞九天[2;37;0m
它是小小的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lyinetd");
        set("owner_name", "小小");
        set_temp("owner", "lyinetd");
        set_temp("owner_name", "小小");
        ::setup();
}
