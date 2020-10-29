// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m拱地小猪[2;37;0m[2;37;0m", ({"xsxs"}));        
        set("gender", "男性");                
        set("long", "拱地小猪[2;37;0m
它是三把手的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xsone");
        set("owner_name", "三把手");
        set_temp("owner", "xsone");
        set_temp("owner_name", "三把手");
        ::setup();
}
