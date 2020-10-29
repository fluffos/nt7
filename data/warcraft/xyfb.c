// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "女性");                
        set("long", "青龙[2;37;0m
它是叶秋雨的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xyfb");
        set("owner_name", "叶秋雨");
        set_temp("owner", "xyfb");
        set_temp("owner_name", "叶秋雨");
        ::setup();
}
