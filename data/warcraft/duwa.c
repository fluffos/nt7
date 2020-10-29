// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m大排量摩托[2;37;0m[2;37;0m", ({"zuoqi"}));        
        set("gender", "男性");                
        set("long", "2000cc[2;37;0m
它是毒娃的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "duwa");
        set("owner_name", "毒娃");
        set_temp("owner", "duwa");
        set_temp("owner_name", "毒娃");
        ::setup();
}
