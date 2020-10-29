// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m赤兔马[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这就是传说中的赤兔，浑身火炭般赤红，龙相虎步、日行万里。[2;37;0m
它是吕布的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lbu");
        set("owner_name", "吕布");
        set_temp("owner", "lbu");
        set_temp("owner_name", "吕布");
        ::setup();
}
