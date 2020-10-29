inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(NOR + MAG "乌骓马" NOR, ({ "wuzhui ma"}));
        set("long", NOR + MAG "此马身高丈许，棕毛直立，通人性，雄丽无比。\n"
                              "乌骓是项羽的坐骑。一直跟随他南征北战，建立功勋无数。\n"
                              "项羽乌江自杀后，将爱马乌骓送给了亭长。亭长带着它过江，但是忠于主\n"
                              "人的乌骓自跳乌江而死。\n" NOR);

        set("tili", 3000);
        set("max_tili", 3000);
        set("level", 3);

        setup();
}