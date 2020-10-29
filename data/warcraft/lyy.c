// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("虎狮兽[2;37;0m[2;37;0m", ({"hss"}));        
        set("gender", "男性");                
        set("long", "那就是一个猛啊，嘿嘿[2;37;0m
它是懒狼狼的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lyy");
        set("owner_name", "懒狼狼");
        set_temp("owner", "lyy");
        set_temp("owner_name", "懒狼狼");
        ::setup();
}
