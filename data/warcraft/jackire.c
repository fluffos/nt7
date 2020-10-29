// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("初晴微雨[1;35m[2;37;0m[2;37;0m", ({"chy"}));        
        set("gender", "女性");                
        set("long", "问世间情为何物    直教人生死相许[2;37;0m
它是予以更换的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "jackire");
        set("owner_name", "予以更换");
        set_temp("owner", "jackire");
        set_temp("owner_name", "予以更换");
        ::setup();
}
