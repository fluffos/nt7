//显示屋宅图样

private int house_picture_user()
{
    message_vision("$n取出一份图纸给$N看了一下，然后收了起来。\n",
                                    this_player(), this_object());
    tell_object(this_player(), "你看到图纸上画着：\n"HIW@PIC

　玲珑屋   　随意阁   　逍遥居  　　　锦绣宅
 ＝＝＝＝   ＝＝＝＝   ＝＝＝＝  ＝＝＝＝＝＝＝＝
‖　　　‖ ‖　　　‖ ‖　后院‖‖　　　后院　　‖
‖　　　‖ ‖　卧室‖ ‖◎　　‖‖　　◎　　　　‖
‖　卧室‖ ‖◎　　‖ ‖｜卧室‖‖　　｜卧室　　‖
‖◎　　‖ ‖｜客厅‖ ‖◎　　‖‖　　◎　　　　‖
‖｜　　‖ ‖◎　　‖ ‖｜客厅‖‖西厢｜厅 东厢 ‖
‖｜大门‖ ‖｜大门‖ ‖◎　　‖‖◎—◎—◎　　‖
‖△　　‖ ‖△　　‖ ‖｜大门‖‖　　｜　　　　‖
‖　　　‖ ‖　　　‖ ‖△　　‖‖　　△大门　　‖
 ＝＝＝＝   ＝＝＝＝   ＝＝＝＝  ＝＝＝＝＝＝＝＝

PIC NOR);
    return 1;
}

private int house_picture_bang()
{
    message_vision("$n取出一份图纸给$N看了一下，然后收了起来。\n",
                                    this_player(), this_object());
    tell_object(this_player(), "你看到图纸上画着：\n"HIW@PIC

　　　 集贤会馆　　　　　　　 聚英山庄
 ＝＝＝＝＝＝＝＝＝＝   ＝＝＝＝＝＝＝＝＝＝
‖　　　　　　　　　‖ ‖　　　　后院　　　‖
‖　　　　后院　　　‖ ‖　　　◎　　　　　‖
‖　　　◎　　　　　‖ ‖　西卧｜主卧　东卧‖
‖　　　｜卧室　　　‖ ‖◎——◎——◎　　‖
‖　　　◎　　　　　‖ ‖｜西厢｜中庭｜东厢‖
‖　议事｜客厅　讲武‖ ‖◎——◎——◎　　‖
‖◎——◎——◎　　‖ ‖｜议事｜客厅｜讲武‖
‖　　　｜武场　　　‖ ‖◎——◎——◎　　‖
‖　　　◎　　　　　‖ ‖　　　｜武场　　　‖
‖　　　｜大门　　　‖ ‖　　　◎　　　　　‖
‖　　　△　　　　　‖ ‖　　　｜大门　　　‖
‖　　　　　　　　　‖ ‖　　　△　　　　　‖
 ＝＝＝＝＝＝＝＝＝＝   ＝＝＝＝＝＝＝＝＝＝

PIC NOR);
    return 1;
}

private int house_picture_xian()
{
    message_vision("$n取出一份图纸给$N看了一下，然后收了起来。\n",
                                    this_player(), this_object());
    tell_object(this_player(), "你看到图纸上画着：\n"HIW@PIC

　　　 广陵逸境
 ＝＝＝＝＝＝＝＝＝＝
‖　　　　后院　　　‖
‖　　　◎┌二楼卧室‖
‖　琴房｜后厅　书斋‖
‖◎——●┴—◎　　‖
‖　　　｜花园　　　‖
‖　　　◎　　　　　‖
‖　西厢｜前厅　东厢‖
‖◎——◎——◎　　‖
‖　　　｜前院　　　‖
‖　　　◎　　　　　‖
‖　　　｜大门　　　‖
‖　　　△　　　　　‖
 ＝＝＝＝＝＝＝＝＝＝

PIC NOR);
    return 1;
}
