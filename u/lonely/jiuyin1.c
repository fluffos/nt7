#include <ansi.h>

void create()
{
        seteuid(getuid());
}

object book = find_object("/clone/lonely/book/zhenjing1");

object get_owner()
{
        object owner;
        if(objectp(book)) {
                owner = environment(book);
                if(owner->is_character()) return owner;
        }
        return 0;
}

object book_owner = get_owner();
nosave string book_owner_name = objectp(book_owner)?query("name", book_owner):"某人";

int do_rumor(string arg)
{
        CHANNEL_D->do_channel(this_object(), "rumor", arg);
        return 1;
}

string get_book()
{
        if(objectp(book)) destruct(book);
        if(objectp(book_owner) && userp(book_owner)) book_owner->unconcious();
        return book_owner_name + "被黄药师打晕了。";
}

nosave mixed *story = ({
        "桃花岛山洞",
        "黄药师：老顽童，听说江湖上" + book_owner_name + "得到了九阴真经上册！你不是说真经上册一直在你这么？",
        "周伯通：哦，是么？不可能吧......",
        "黄药师：你骗了我这么久！居然把真经给了别人！！！接我的碧海潮生曲！！",
        "周伯通：等等！！！我肚子痛！",
        "黄药师：·#￥！%",
        "周伯通：黄老邪，不是我怕你！真经真的还在我这！！",
        "黄药师：那拿出来让我瞧瞧！",
        "周伯通：不行，我拿出来你就抢了！",
        "黄药师：我看是你早就给人了！我们一同出去，若是让我发现真经在别人那里，哼哼~",
        "周伯通：怎么样？",
        "黄药师：我就宰了你！",
        "周伯通：......（就你那能耐，呸，打的赢我吗？）",
        (: do_rumor, "黄药师与周伯通为九阴真经出了桃花岛......" :),
        "三天后",
        (: get_book :),
        "黄药师：如何，这就是从他身上搜出的真经！！！",
        "周伯通（翻了两下）：明明是无字书啊！！",
        "黄药师、" + book_owner_name + "：不可能！！！",
        book_owner_name + "心想：我都拿了3天，看了无数遍，如何可能是无字书？？？？？？",
        "黄药师翻了两下：真的无字书！！",
        "周伯通暗自偷乐：真经原本早就被我毁了！现在的都是我默写出来的！\n"
        "我都用草汁写在纸上，一见光3天后字迹就消失！任你黄老邪奸似鬼，还不是喝我的洗脚水！",
        "黄老邪：好，只要真经不在别人那里就行，跟我回桃花岛。",
        "周伯通：你......·#￥%",
});

string prompt() { return HIW "【武林轶事】" NOR; }

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}
