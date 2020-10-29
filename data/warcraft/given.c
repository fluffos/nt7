// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m汗血宝马[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "汗血宝马[2;37;0m
它是血轮眼的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "given");
        set("owner_name", "血轮眼");
        set_temp("owner", "given");
        set_temp("owner_name", "血轮眼");
        ::setup();
}
