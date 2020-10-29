
//转世任务主控文件
#include <ansi.h>

inherit F_DBASE;

#define JINGYAN  "/d/jingyan/migong1"
#define QILIN  "/d/zhuanshi/qilindong/dongkou"
#define WUDIE  "/d/wudie/shanlu1"

void jingyan_close(object n_place);
void wudie_close(object n_place);
void qilin_close(object place);

mapping dir_list = ([
"北京" : "/d/beijing/",
"长安" : "/d/changan/",
"扬州" : "/d/city/",
"成都" : "/d/city3/",
"大理" : "/d/dali/",
"佛山" : "/d/foshan/",
"福州" : "/d/fuzhou/",
"关外" : "/d/guanwai/",
"杭州" : "/d/hangzhou/",
"恒山" : "/d/hengshan/",
"荆州" : "/d/jingzhou/",
"开封" : "/d/kaifeng/",
"华山" : "/d/huashan/",
"昆明" : "/d/kunming/",
"兰州" : "/d/lanzhou/",
"灵州" : "/d/lingzhou/",
"洛阳" : "/d/luoyang/",
"嵩山" : "/d/songshan/",
"苏州" : "/d/suzhou/",
"泰山" : "/d/taishan/",
"武当山" : "/d/wudang/",
"襄阳" : "/d/xiangyang/",
"中州" : "/d/zhongzhou/",
]);

array place = values(dir_list);
array c_place = keys(dir_list);

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "转世精灵");
        CHANNEL_D->do_channel( this_object(), "wiz", "转世精灵启动。"); 
        //惊雁宫入口
        remove_call_out("jingyan_open");
        call_out("jingyan_open", 350);
                //舞蝶入口
        remove_call_out("wudie_open");
        call_out("wudie_open", 350);
       //麒麟窟入口
        remove_call_out("qilin_open");
        call_out("qilin_open", 550);
}

void jingyan_open()
{       
        object n_place;
        string s_place, dir;
        int i;
        int num = random(sizeof(place));
        string city = place[num];

        array plist = get_dir(city);

        do {       
                s_place = plist[random(sizeof(plist))];     
                //文件名中含有bak的文件不要，继续找下一个
                if ( strsrch(s_place,"bak") > -1 ) continue; 
                //不是c文件的也滤过
                i = sizeof(s_place);
                if ( s_place[(i-2)..i] != ".c" ) continue;
                //如果该房间已经调出在内存里的直接find
                //find不到说明没调出在内存里，那就load出来 
                //load也load不出来大概就有问题了，那就找下一个了   
                if ( ! objectp(n_place = find_object(city + s_place)))
               
                if ( ! objectp(n_place = load_object(city + s_place)))
                   continue; 
           }       
        while(!n_place || !n_place->query("outdoors"));
                
        n_place->set("exits/jingyangong", JINGYAN);

               
       CHANNEL_D->do_channel(this_object(), 
         "wiz", "惊雁宫入口连接到了" + c_place[num] + city + s_place + "请注意。");
                
       set("jingyan/out", city + s_place); //主文件里记录下迷宫的连接处
                                          
       message("vision", HIG"【" HIR "江湖传言" HIG"】" HIW 
               "：神秘的惊雁宫重现江湖了，似乎在"
               + c_place[num] + "方向。\n" + NOR,users());
       //10分钟后关闭，时间可以设置

       remove_call_out("jingyan_close");
       call_out("jingyan_close", 600, n_place);      
}

void jingyan_close(object n_place)
{       
     if (n_place && n_place->query("exits/jingyangong"))
     {       
       n_place->delete("exits/jingyangong");       
       message("vision", HIG"【" HIR"江湖传言" HIG"】" HIW"：神秘的惊雁宫又消失了。\n" 
                      NOR,users());
     }
     remove_call_out("jingyan_open");
   //  call_out("jingyan_open", 3600 * 3); //定三小时开一次口
     call_out("jingyan_open", 1800); //测试时定半小时开一次口

}
void wudie_open()
{       
        object n_place;
        string s_place, dir;
        int i;
        int num = random(sizeof(place));
        string city = place[num];

        array plist = get_dir(city);

        do {       
                s_place = plist[random(sizeof(plist))];     
                //文件名中含有bak的文件不要，继续找下一个
                if ( strsrch(s_place,"bak") > -1 ) continue; 
                //不是c文件的也滤过
                i = sizeof(s_place);
                if ( s_place[(i-2)..i] != ".c" ) continue;
                //如果该房间已经调出在内存里的直接find
                //find不到说明没调出在内存里，那就load出来 
                //load也load不出来大概就有问题了，那就找下一个了   
                if ( ! objectp(n_place = find_object(city + s_place)))
               
                if ( ! objectp(n_place = load_object(city + s_place)))
                   continue; 
           }       
        while(!n_place || !n_place->query("outdoors"));
                
        n_place->set("exits/wudie", WUDIE);

               
       CHANNEL_D->do_channel(this_object(), 
         "wiz", "舞蝶山庄连接到了" + c_place[num] + city + s_place + "请注意。");
                
       set("wudie/out", city + s_place); //主文件里记录下迷宫的连接处
                                          
       message("vision", HIG"【" HIR "神秘门派" HIG"】" HIW 
               "：传说中的舞蝶山庄重现江湖了，似乎在"
               + c_place[num] + "方向。\n" + NOR,users());
       //10分钟后关闭，时间可以设置

       remove_call_out("wudie_close");
       call_out("wudie_close", 600, n_place);      
}

void wudie_close(object n_place)
{       
     if (n_place && n_place->query("exits/wudie"))
     {       
       n_place->delete("exits/wudie");       
       message("vision", HIG"【" HIR"神秘门派" HIG"】" HIW"：传说中的舞蝶山庄又消失了。\n" 
                      NOR,users());
     }
     remove_call_out("wudie_open");
   //  call_out("jingyan_open", 3600 * 3); //定三小时开一次口
     call_out("wudie_open", 1800); //测试时定半小时开一次口

}

void qilin_open()
{
     object room = find_object("/d/city3/shudao8");
     if (! room)
       room = load_object("/d/city3/shudao8");

    room->set("exits/qilinku", QILIN);
    
     message("vision", HIG"【" HIR"江湖传言" HIG"】" HIW
                "：成都城外洪水退去，麒麟窟重现世间。\n"NOR,users());
      
    remove_call_out("qilin_close");
    call_out("qilin_close", 600, room); //十分种后关闭
}

void qilin_close(object room)
{
     if ( room && room->query("exits/qilinku"));
         room->delete("exits/qilinku");

     message("vision", HIG"【" HIR"江湖传言" HIG"】" HIW
                "：成都城外洪水汹涌，麒麟窟再次消失在人世间。\n"NOR,users());

    remove_call_out("qilin_open");
  //  call_out("qilin_open", 3600 * 6); //定六小时开一次口
   call_out("qilin_open", 1800); //测试时定半小时开一次口

}



