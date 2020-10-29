// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("我的龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "龙[2;37;0m
它是李二十的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cxunbao");
        set("owner_name", "李二十");
        set_temp("owner", "cxunbao");
        set_temp("owner_name", "李二十");
        ::setup();
}
