#include "_freecplus.h"

void help()
{
   printf("本程序用于字符集转化批处理\n");
   printf("程序使用格式:\n");
   printf("transform 目录名 原字符集 转化字符集 true/flase(是否删除原目录)\n");
   printf("例如:transform /transform gbk utf-8 true\n\n");
}

int main(int argc,char *argv[])
{
   CDir dir;

   if( argc < 5 )
   {
      printf("\n参数出错\n\n");
      help();
      return -1;
   }

   if( opendir(argv[1]) == 0 )
   {
      printf("目录不存在\n");
      return -1;
   }

   dir.OpenDir(argv[1],"*",100,true,false);

   while( dir.ReadDir() )
   {
      char command_iconv[101];
      char create_dir[101];
      
      //生成命令
      SPRINTF(command_iconv,sizeof(command_iconv), \
      "iconv -f %s -t %s %s -o %s.%s%s",argv[2],argv[3],dir.m_FullFileName,argv[1],argv[3],dir.m_FullFileName + strlen(argv[1]));
      
      //生成目录
      SPRINTF(create_dir,sizeof(create_dir), \
      "%s.%s%s",argv[1],argv[3],dir.m_FullFileName + strlen(argv[1]));
      MKDIR(create_dir,true);

      printf("执行命令:%s\n",command_iconv);
      system(command_iconv);
   }

   if( MatchStr(argv[4],"true") )
   {
      char command_rm[101];
      char command_mv[101];

      SPRINTF(command_rm,sizeof(command_rm),"rm -rf %s",argv[1]);
      printf("执行命令:%s\n",command_rm);
      system(command_rm);

      SPRINTF(command_mv,sizeof(command_mv),"mv %s.%s %s",argv[1],argv[3],argv[1]);
      printf("执行命令:%s\n",command_mv);
      system(command_mv);
   }

   return 0;
}
