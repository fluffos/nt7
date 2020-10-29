// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("灵芝瑞兽麒麟[2;37;0m[2;37;0m", ({"huashanxmride"}));        
        set("gender", "女性");                
        set("long", "灵芝瑞兽麒麟[2;37;0m
它是岳灵芝的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "huashanxm");
        set("owner_name", "岳灵芝");
        set_temp("owner", "huashanxm");
        set_temp("owner_name", "岳灵芝");
        ::setup();
}
