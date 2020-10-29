// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("看看天[2;37;0m[2;37;0m", ({"xianzhim"}));        
        set("gender", "男性");                
        set("long", "没有[2;37;0m
它是世界尽头的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xianzhi");
        set("owner_name", "世界尽头");
        set_temp("owner", "xianzhi");
        set_temp("owner_name", "世界尽头");
        ::setup();
}
