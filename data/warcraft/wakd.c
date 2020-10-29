// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"xiaoq"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是嘿羞的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wakd");
        set("owner_name", "嘿羞");
        set_temp("owner", "wakd");
        set_temp("owner_name", "嘿羞");
        ::setup();
}
