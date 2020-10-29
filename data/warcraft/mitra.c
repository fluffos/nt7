// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("翱翔[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "一只翱翔在天的朱雀[2;37;0m
它是皇甫崇仁的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "mitra");
        set("owner_name", "皇甫崇仁");
        set_temp("owner", "mitra");
        set_temp("owner_name", "皇甫崇仁");
        ::setup();
}
