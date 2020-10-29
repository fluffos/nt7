// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"baihui"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是黄埔小的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "skpj");
        set("owner_name", "黄埔小");
        set_temp("owner", "skpj");
        set_temp("owner_name", "黄埔小");
        ::setup();
}
