// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m诗意[2;37;0m[2;37;0m", ({"picsyi"}));        
        set("gender", "男性");                
        set("long", "$HIY$诗意!1[2;37;0m
它是陆卜拾遗的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dangsyi");
        set("owner_name", "陆卜拾遗");
        set_temp("owner", "dangsyi");
        set_temp("owner_name", "陆卜拾遗");
        ::setup();
}
