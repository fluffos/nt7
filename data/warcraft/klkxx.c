// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"klxxd"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是硝酸甘油的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "klkxx");
        set("owner_name", "硝酸甘油");
        set_temp("owner", "klkxx");
        set_temp("owner_name", "硝酸甘油");
        ::setup();
}
