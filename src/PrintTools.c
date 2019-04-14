/***************************************************
* See PrintTools.h for module description.         *
***************************************************/
#include<unistd.h>
#include<sys/uio.h>
#include<string.h>

	/*******************
	* See PrintTools.h *
	*******************/
	int printStrCat(const int fd,char *str1,char *str2,const int str1len,const int str2len){
		// Test that POSIX.1-2001 is in use.
		#if _POSIX_C_SOURCE>=200112L
			// Use system call writev so we don't need to copy to buffer.
			const struct iovec io[2]={{str1,str1len},{str2,str2len}};
			return writev(fd,io,sizeof(io)/sizeof(struct iovec));
		#else
			// Just create the full buffer since this would not be used with
			// long files where we would care about optimal buffer size.
			const size_t iobufferlen=str1len+str2len;
			char iobuffer[iobufferlen];
			memcpy(iobuffer,str1,str1len);
			memcpy(iobuffer+str1len,str2,str2len);
			return write(fd,iobuffer,iobufferlen);
		#endif /* _POSIX_C_SOURCE */
	}
	/*******************
	* See PrintTools.h *
	*******************/
	int printStrCat3(const int fd,char *str1,char *str2,char *str3,const int str1len,const int str2len,const int str3len){
		#if _POSIX_C_SOURCE>=200112L
			const struct iovec io[]={{str1,str1len},{str2,str2len},{str3,str3len}};
			return writev(fd,io,sizeof(io)/sizeof(struct iovec));
		#else
			const size_t iobufferlen=str1len+str2len+str3len;
			char iobuffer[iobufferlen];
			memcpy(iobuffer,str1,str1len);
			memcpy(iobuffer+str1len,str2,str2len);
			memcpy(iobuffer+str1len+str2len,str3,str3len);
			return write(fd,iobuffer,iobufferlen);
		#endif /* _POSIX_C_SOURCE */
	}
