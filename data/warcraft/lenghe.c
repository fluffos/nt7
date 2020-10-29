// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("它它它[2;37;0m[2;37;0m", ({"tatata"}));        
        set("gender", "男性");                
        set("long", "它它它[2;37;0m
它是冷赫的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lenghe");
        set("owner_name", "冷赫");
        set_temp("owner", "lenghe");
        set_temp("owner_name", "冷赫");
        ::setup();
}
