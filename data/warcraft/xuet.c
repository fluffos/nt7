// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m涛涛[2;37;0m[2;37;0m", ({"xuets"}));        
        set("gender", "男性");                
        set("long", "嘿嘿[2;37;0m
它是薛涛的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xuet");
        set("owner_name", "薛涛");
        set_temp("owner", "xuet");
        set_temp("owner_name", "薛涛");
        ::setup();
}
