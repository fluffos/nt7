// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m输出文字中[2;37;0m[2;37;0m", ({"bmw"}));        
        set("gender", "男性");                
        set("long", "bmw[2;37;0m
它是擦脸明媚的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "caimm");
        set("owner_name", "擦脸明媚");
        set_temp("owner", "caimm");
        set_temp("owner_name", "擦脸明媚");
        ::setup();
}
