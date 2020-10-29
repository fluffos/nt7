// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("坐骑[2;37;0m[2;37;0m", ({"zuoqizu"}));        
        set("gender", "男性");                
        set("long", "坐骑[2;37;0m
它是药卒的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaozu");
        set("owner_name", "药卒");
        set_temp("owner", "yaozu");
        set_temp("owner_name", "药卒");
        ::setup();
}
