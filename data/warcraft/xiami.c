// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"xiamii"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是小虾米的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xiami");
        set("owner_name", "小虾米");
        set_temp("owner", "xiami");
        set_temp("owner_name", "小虾米");
        ::setup();
}
