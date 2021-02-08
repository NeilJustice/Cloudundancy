import inspect
import logging

def caller_decorated_message(message):
   callerFunctionName = inspect.stack()[2][3] + '() -'
   callerDecoratedMessage = callerFunctionName + ' ' + message
   return callerDecoratedMessage

def log_info(message):
   callerDecoratedMessage = caller_decorated_message(message)
   logger.info(callerDecoratedMessage)

def log_exception(message):
   callerFunctionName = caller_decorated_message(message)
   logger.exception(callerFunctionName)

logging.basicConfig(level=logging.INFO)
loggingFileHandler = logging.FileHandler('log.txt')
loggingFormatter = logging.Formatter('%(asctime)s %(name)s %(levelname)s %(message)s')
loggingFileHandler.setFormatter(loggingFormatter)

logger = logging.getLogger(__name__)
logger.addHandler(loggingFileHandler)
