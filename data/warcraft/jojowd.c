// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m野鸡[2;37;0m[2;37;0m", ({"yeji"}));        
        set("gender", "女性");                
        set("long", "一只野鸡。[2;37;0m
它是史玉柱的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "jojowd");
        set("owner_name", "史玉柱");
        set_temp("owner", "jojowd");
        set_temp("owner_name", "史玉柱");
        ::setup();
}
