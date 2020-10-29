// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火袭[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "嘿嘿[2;37;0m
它是楚米一的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "uliana");
        set("owner_name", "楚米一");
        set_temp("owner", "uliana");
        set_temp("owner_name", "楚米一");
        ::setup();
}
