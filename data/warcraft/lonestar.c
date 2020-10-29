// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m本田[2;37;0m[2;37;0m", ({"toyota"}));        
        set("gender", "女性");                
        set("long", "this is toyota[2;37;0m
它是孤星的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lonestar");
        set("owner_name", "孤星");
        set_temp("owner", "lonestar");
        set_temp("owner_name", "孤星");
        ::setup();
}
