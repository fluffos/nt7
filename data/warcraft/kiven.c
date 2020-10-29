// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小帅哥[2;37;0m[2;37;0m", ({"iambear"}));        
        set("gender", "男性");                
        set("long", "帅气的少年。[2;37;0m
它是唐宇翔的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kiven");
        set("owner_name", "唐宇翔");
        set_temp("owner", "kiven");
        set_temp("owner_name", "唐宇翔");
        ::setup();
}
