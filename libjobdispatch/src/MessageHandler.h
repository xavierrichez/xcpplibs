#ifndef MESSAGEHANDLER_H_
#define MESSAGEHANDLER_H_

template <class T> class MessageHandler
{
public:
	virtual ~MessageHandler() {;}

	virtual void notifyMessage(const T *messageData)=0;
};

#endif /* MESSAGEHANDLER_H_ */
