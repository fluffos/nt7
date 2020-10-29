// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白素贞[2;37;0m[2;37;0m", ({"miss"}));        
        set("gender", "女性");                
        set("long", "一条很白的长虫，长吗？长！白吗？白！[2;37;0m
它是李淳罡的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "swordcome");
        set("owner_name", "李淳罡");
        set_temp("owner", "swordcome");
        set_temp("owner_name", "李淳罡");
        ::setup();
}
