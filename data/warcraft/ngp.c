// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m飞韵[2;37;0m[2;37;0m", ({"mimi"}));        
        set("gender", "女性");                
        set("long", "有点可爱，有点萌[2;37;0m
它是南宫萍的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ngp");
        set("owner_name", "南宫萍");
        set_temp("owner", "ngp");
        set_temp("owner_name", "南宫萍");
        ::setup();
}
