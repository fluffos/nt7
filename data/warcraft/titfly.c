// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小叶[2;37;0m[2;37;0m", ({"palaxiao"}));        
        set("gender", "女性");                
        set("long", "小叶[2;37;0m
它是提坦莉娅的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "titfly");
        set("owner_name", "提坦莉娅");
        set_temp("owner", "titfly");
        set_temp("owner_name", "提坦莉娅");
        ::setup();
}
