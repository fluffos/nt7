// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m黄鹤楼[2;37;0m[2;37;0m", ({"cigarette"}));        
        set("gender", "男性");                
        set("long", "~黄鹤楼~[2;37;0m
它是王安石的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wanganshi");
        set("owner_name", "王安石");
        set_temp("owner", "wanganshi");
        set_temp("owner_name", "王安石");
        ::setup();
}
