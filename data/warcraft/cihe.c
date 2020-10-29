// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("日[2;37;0m[2;37;0m", ({"gygy"}));        
        set("gender", "男性");                
        set("long", "日[2;37;0m
它是眼五五的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cihe");
        set("owner_name", "眼五五");
        set_temp("owner", "cihe");
        set_temp("owner_name", "眼五五");
        ::setup();
}
