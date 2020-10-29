// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;34m星星[2;37;0m[2;37;0m", ({"xingxing"}));        
        set("gender", "女性");                
        set("long", "满天星星[2;37;0m
它是星光的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xingguang");
        set("owner_name", "星光");
        set_temp("owner", "xingguang");
        set_temp("owner_name", "星光");
        ::setup();
}
