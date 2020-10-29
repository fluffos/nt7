// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("花虎[2;37;0m[2;37;0m", ({"huahu"}));        
        set("gender", "男性");                
        set("long", "花虎[2;37;0m
它是康梓二的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "kcmq");
        set("owner_name", "康梓二");
        set_temp("owner", "kcmq");
        set_temp("owner_name", "康梓二");
        ::setup();
}
