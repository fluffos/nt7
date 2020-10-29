// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m羽月希[1;37m[2;37;0m[2;37;0m", ({"yuyuexi"}));        
        set("gender", "女性");                
        set("long", "AV[2;37;0m
它是粽少的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zrz");
        set("owner_name", "粽少");
        set_temp("owner", "zrz");
        set_temp("owner_name", "粽少");
        ::setup();
}
