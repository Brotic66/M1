/**
 * @file AreteException.scala
 * @author brice VICO
 * @date 09/05/2015
 */

package Exception

import scala.util.control.Exception

class AreteException(message: String, nestedException: Throwable) extends Exception(message, nestedException)
{     
    def this(message: String) = this(message, null)
}