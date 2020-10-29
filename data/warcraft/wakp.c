// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小青龙[2;37;0m[2;37;0m", ({"xiaoq"}));        
        set("gender", "男性");                
        set("long", "小青龙[2;37;0m
它是罗十的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wakp");
        set("owner_name", "罗十");
        set_temp("owner", "wakp");
        set_temp("owner_name", "罗十");
        ::setup();
}
