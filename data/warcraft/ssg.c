// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m搓搓搓搓搓搓[2;37;0m[2;37;0m", ({"qwe"}));        
        set("gender", "女性");                
        set("long", "搓搓搓搓搓搓[2;37;0m
它是搓丸子的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ssg");
        set("owner_name", "搓丸子");
        set_temp("owner", "ssg");
        set_temp("owner_name", "搓丸子");
        ::setup();
}
