mapping menpai1=([
        "玄慈大师":   "少林派",
        "宋远桥":     "武当派",
        "灭绝师太":   "峨嵋派",
        "洪七公":     "丐帮",
        "岳不群":     "华山派",
        "张无忌":     "明教",
        "小龙女":     "古墓派",
        "丘处机":     "全真教",
        //"陈近南":     "云龙门",
]);

mapping menpai2=([
        "丁春秋":     "星宿派",
        "洪安通":     "神龙教",
        "何铁手":     "五毒教",
        "欧阳峰":     "欧阳世家",
        "慕容复":     "慕容世家",
        //"邀月宫主":   "移花宫",  
        "苏星河":     "逍遥派",
        "天山童姥":   "灵鹫宫",
        //"黄药师":     "桃花岛",
        "唐老太太":   "唐门世家",   
]);

string *master1=({
        "玄慈大师",
        "宋远桥",
        "灭绝师太",
        "洪七公",
        "岳不群",
        "张无忌",
        "小龙女",
        "丘处机",
        //"陈近南",
});

string *master2=({
        "丁春秋",
        "洪安通",
        "何铁手",
        "欧阳峰",
        "慕容复",
        //"邀月宫主", 
        "苏星河",
        "天山童姥",
        //"黄药师",   
        "唐老太太",
});

nosave string fam1;
nosave string fam2;

int chousha_begin()
{
        int i,j,k;
        object *ulist;


        i=random(sizeof(master1));
        j=random(sizeof(master2));
        ulist=users();
        k=sizeof(ulist);

        fam1=menpai1[master1[i]];
        fam2=menpai2[master2[j]];
        
        CHANNEL_D->channel_broadcast("mess", master1[i]+"："+fam1+"门下弟子听令，命你们在一个时辰内将"+fam2+"彻底击溃，以匡武林正义！");
        CHANNEL_D->channel_broadcast("mess", master2[j]+"："+fam2+"弟子听令，命你们在一个时辰内将"+fam1+"彻底荡平，让他们尝尝我们的厉害！");

        while (k-- )
        {
                if ( !environment(ulist[k]) ) continue;

                if (ulist[k]->query_family() == fam1)
                        set_temp("chousha/fam",fam2,ulist[k]);
                else if (ulist[k]->query_family() == fam2)
                        set_temp("chousha/fam",fam1,ulist[k]);
        }
        set_temp("chousha/fam1",fam1,this_object()); 
        set_temp("chousha/fam2",fam2,this_object());
        write_file("/quest/quest4/fam1",fam1,1);
        write_file("/quest/quest4/fam2",fam2,1); 

        call_out("chousha_close", 1800);
        return 1;
}


void chousha_close()
{
        object *ulist;
        int k;

        ulist=users();
        k=sizeof(ulist);

        while (k--)
        {
                if ( !environment(ulist[k]) ) continue;
                if (query_temp("chousha",ulist[k]))
                {
                        delete_temp("chousha",ulist[k]);
                        tell_object(ulist[k], BLINK"忽然你心中生起一股厌倦的感觉，"
                                                   "开始疑惑的这样的江湖仇杀有何意义，\n"
                                                   "你看着自己沾满鲜血的手，开始不断地问自己为什么？为什么？.....\n"NOR);
                } 
        }

        CHANNEL_D->channel_broadcast("mess", "历时半月的"+fam1+"与"+fam2+"之间的仇杀终于结束了，双方皆死伤无数！");
        delete_temp("chousha",this_object());

        return;
}