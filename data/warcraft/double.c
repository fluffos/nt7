// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m李鹏高[2;37;0m[2;37;0m", ({"newdouble"}));        
        set("gender", "男性");                
        set("long", "void[2;37;0m
它是名字接近的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "double");
        set("owner_name", "名字接近");
        set_temp("owner", "double");
        set_temp("owner_name", "名字接近");
        ::setup();
}
